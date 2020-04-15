from qmk.commands import run, PIPE


def check_subcommand(command, *args):
    cmd = ['bin/qmk', command] + list(args)
    return run(cmd, stdout=PIPE, stderr=PIPE, universal_newlines=True)


def test_cformat():
    result = check_subcommand('cformat', 'quantum/matrix.c')
    assert result.returncode == 0


def test_compile():
    assert check_subcommand('compile', '-kb', 'handwired/onekey/pytest', '-km', 'default').returncode == 0


def test_compile_json():
    assert check_subcommand('compile', '-kb', 'handwired/onekey/pytest', '-km', 'default_json').returncode == 0


def test_flash():
    assert check_subcommand('flash', '-b').returncode == 1
    assert check_subcommand('flash').returncode == 1


def test_config():
    result = check_subcommand('config')
    assert result.returncode == 0
    assert 'general.color' in result.stdout


def test_kle2json():
    assert check_subcommand('kle2json', 'kle.txt', '-f').returncode == 0


def test_doctor():
    result = check_subcommand('doctor', '-n')
    assert result.returncode == 0
    assert 'QMK Doctor is checking your environment.' in result.stderr
    assert 'QMK is ready to go' in result.stderr


def test_hello():
    result = check_subcommand('hello')
    assert result.returncode == 0
    assert 'Hello,' in result.stderr


def test_pyformat():
    result = check_subcommand('pyformat')
    assert result.returncode == 0
    assert 'Successfully formatted the python code' in result.stderr


def test_list_keyboards():
    result = check_subcommand('list-keyboards')
    assert result.returncode == 0
    # check to see if a known keyboard is returned
    # this will fail if handwired/onekey/pytest is removed
    assert 'handwired/onekey/pytest' in result.stdout


def test_list_keymaps():
    result = check_subcommand("list-keymaps", "-kb", "handwired/onekey/pytest")
    assert result.returncode == 0
    assert "default" and "default_json" and "test" in result.stdout


def test_list_keymaps_no_keyboard_found():
    result = check_subcommand("list-keymaps", "-kb", "asdfghjkl")
    assert result.returncode == 0
    assert "does not exist" in result.stdout


def test_c2json():
    result = check_subcommand("c2json", "-kb", "handwired/onekey/pytest", "keyboards/handwired/onekey/keymaps/pytest/keymap.c")
    assert result.returncode == 0
    assert result.stdout.strip() == '{"keyboard": "handwired/onekey/pytest", "documentation": "This file is a keymap.json file for handwired/onekey/pytest", "layout": "LAYOUT", "layers": [["KC_ENTER"]]}'


def test_c2json_nocpp():
    result = check_subcommand("c2json", "--no-cpp", "-kb", "handwired/onekey/pytest", "keyboards/handwired/onekey/keymaps/pytest_nocpp/keymap.c")
    assert result.returncode == 0
    assert result.stdout.strip() == '{"keyboard": "handwired/onekey/pytest", "documentation": "This file is a keymap.json file for handwired/onekey/pytest", "layout": "LAYOUT", "layers": [["KC_ENTER"]]}'
