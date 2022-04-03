# awesome cli on Mac

> cli stands for command line interface

## homebrew

refer

- [homebrew cheetsheet](https://devhints.io/homebrew)
- [Homebrew Documentation](https://docs.brew.sh/)

### package management

| command              |                             |
| -------------------- | --------------------------- |
| `brew install git`   | Install a package           |
| `brew uninstall git` | Remove/Uninstall a package  |
| `brew upgrade git`   | Upgrade a package           |
| `brew info git`      | List versions, caveats, etc |
| `brew cleanup git`   | Remove old versions         |

#### global command

`brew list`  List installed packages

### services

1. [`sudo`] `brew services` [`list`]
   List all managed services for the current user (or root).
2. `sudo`] `brew services start` (*`formula`*|`--all`)
   Start the service *`formula`* immediately and register it to launch at login (or boot).
3. [`sudo`] `brew services stop` (*`formula`*|`--all`)
   Stop the service *`formula`* immediately and unregister it from launching at login (or boot).
4. [`sudo`] `brew services restart` (*`formula`*|`--all`)
   Stop (if necessary) and start the service *`formula`* immediately and register it to launch at login (or boot).

the logs are stored to `/usr/local/var/log`

## tmux

### Pane VS Window VS Session

<img src="https://arcolinux.com/wp-content/uploads/2020/02/tmux-server.png" style="zoom:67%;" />

### manipulate

> `C-b` following means prefix which for me is `C-a`
>
> reload config file: `tmux source-file ~/.tmux.cong`

open a new session: `tmux new -s session_name`

kill a session: `tmux kill-session -t session_name `

list sessions: `tmux ls`

open a new window: `tmux new-window` shortcut:`C-b c`

close a window: `tmux kill-window -t window_number`

attach to a session: `tmux a(attach) -t session_name`

detach: `C-b d`

switch between sessions: `C-b (\)`

install new plugin using tpm：`C-b I` (it will fetch package from Internet and reload tmux conf)

`tmux send-keys -t {session}:{window}.{pane}`