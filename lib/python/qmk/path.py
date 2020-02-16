"""Functions that help us work with files and folders.
"""
import logging
import os
from pathlib import Path
import functools

from milc import cli

from qmk.constants import QMK_FIRMWARE, MAX_KEYBOARD_SUBFOLDERS
from qmk.errors import NoSuchKeyboardError


def is_keymap_dir(keymap_path):
    """Returns True if `keymap_path` is a valid keymap directory.
    """
    keymap_path = Path(keymap_path)
    keymap_c = keymap_path / 'keymap.c'
    keymap_json = keymap_path / 'keymap.json'

    return any((keymap_c.exists(), keymap_json.exists()))


def is_keyboard(keyboard_name):
    """Returns True if `keyboard_name` is a keyboard we can compile.
    """
    keyboard_path = QMK_FIRMWARE / 'keyboards' / keyboard_name
    rules_mk = keyboard_path / 'rules.mk'
    return rules_mk.exists()


def under_qmk_firmware():
    """Returns a Path object representing the relative path under qmk_firmware, or None.
    """
    cwd = Path(os.environ['ORIG_CWD'])

    try:
        return cwd.relative_to(QMK_FIRMWARE)
    except ValueError:
        return None


def keymap(keyboard):
    """Locate the correct directory for storing a keymap.

    Args:

        keyboard
            The name of the keyboard. Example: clueboard/66/rev3
    """
    keyboard_folder = Path('keyboards') / keyboard

    for i in range(MAX_KEYBOARD_SUBFOLDERS):
        if (keyboard_folder / 'keymaps').exists():
            return (keyboard_folder / 'keymaps').resolve()

        keyboard_folder = keyboard_folder.parent

    logging.error('Could not find the keymaps directory!')
    raise NoSuchKeyboardError('Could not find keymaps directory for: %s' % keyboard)


def normpath(path):
    """Returns a `pathlib.Path()` object for a given path.

    This will use the path to a file as seen from the directory the script was called from. You should use this to normalize filenames supplied from the command line.
    """
    path = Path(path)

    if path.is_absolute():
        return Path(path)

    return Path(os.environ['ORIG_CWD']) / path


def context_sensitivity(func):
    """Returns `(keyboard_name, keymap_name)` based on the user's current environment.

    This determines the keyboard and keymap name using the following precedence order:

        * Command line flags (--keyboard and --keymap)
        * Current working directory
            * `keyboards/<keyboard_name>`
            * `keyboards/<keyboard_name>/keymaps/<keymap_name>`
            * `layouts/**/<keymap_name>`
            * `users/<keymap_name>`
        * Configuration
            * cli.config.<subcommand>.keyboard
            * cli.config.<subcommand>.keymap
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        print(cli.config[cli._entrypoint.__name__]['keyboard'])

        # Check to make sure their copy of MILC supports config_source
        if not hasattr(cli, 'config_source'):
            cli.log.error("Your QMK CLI is out of date. Please upgrade using pip3 or your package manager.")
            exit(1)

        # State variables
        relative_cwd = under_qmk_firmware()
        keyboard_name = ""
        keymap_name = ""

        # If the keyboard or keymap are passed as arguments use that in preference to anything else
        if cli.config_source[cli._entrypoint.__name__]['keyboard'] == 'argument':
            keyboard_name = cli.config[cli._entrypoint.__name__]['keyboard']
        if cli.config_source[cli._entrypoint.__name__]['keymap'] == 'argument':
            keymap_name = cli.config[cli._entrypoint.__name__]['keymap']

        if not keyboard_name or not keymap_name:
            # If we don't have a keyboard_name and keymap_name from arguments try to derive one or both
            if relative_cwd and relative_cwd.parts and relative_cwd.parts[0] == 'keyboards':
                # Try to determine the keyboard and/or keymap name
                current_path = Path('/'.join(relative_cwd.parts[1:]))

                if current_path.parts[-2] == 'keymaps':
                    if not keymap_name:
                        keymap_name = current_path.parts[-1]
                    if not keyboard_name:
                        keyboard_name = '/'.join(current_path.parts[:-2])
                elif not keyboard_name and is_keyboard(current_path):
                    keyboard_name = str(current_path)

            elif relative_cwd and relative_cwd.parts and relative_cwd.parts[0] == 'layouts':
                # Try to determine the keymap name from the community layout
                if is_keymap_dir(relative_cwd) and not keymap_name:
                    keymap_name = relative_cwd.name

            elif relative_cwd and relative_cwd.parts and relative_cwd.parts[0] == 'users':
                # Try to determine the keymap name based on which userspace they're in
                if not keymap_name and len(relative_cwd.parts) > 1:
                    keymap_name = relative_cwd.parts[1]

        # If we still don't have a keyboard and keymap check the config
        if not keyboard_name and cli.config[cli._entrypoint.__name__]['keyboard']:
            keyboard_name = cli.config[cli._entrypoint.__name__]['keyboard']

        if not keymap_name and cli.config[cli._entrypoint.__name__]['keymap']:
            keymap_name = cli.config[cli._entrypoint.__name__]['keymap']

        cli.config[cli._entrypoint.__name__]['keyboard'] = keyboard_name
        cli.config[cli._entrypoint.__name__]['keymap'] = keymap_name

        return func(*args, **kwargs)

    return wrapper
