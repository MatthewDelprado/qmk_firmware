# close-out config — GMK (Matt's qmk_firmware fork)

## Git
- Work happens on feature branches (`feat/<board>-matt-keymap`), never on `master`, which tracks qmk upstream.
- Push the current branch to the `fork` remote (`MatthewDelprado/qmk_firmware`) as a backup. Never push to `origin` (qmk/qmk_firmware) and don't open PRs upstream.
- The repo lives in iCloud-synced `~/Documents`; if `qmk compile` hangs at 0% CPU, files are iCloud placeholders — `brctl download` them or set the folder to Keep Downloaded.

## Issues
- No tracker: the fork has issues disabled and qmk upstream isn't ours. Skip Step 5.
