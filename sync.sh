#!/usr/bin/env bash

set -euo pipefail

UPSTREAM_URL="https://github.com/Induaditya3/PCC-CS391.git"
TARGET_BRANCH="main"
LOG_FILE="${XDG_STATE_HOME:-$HOME/.local/state}/pcc-cs391/sync.log"
SYNC_TIMEOUT_SECONDS="${SYNC_TIMEOUT_SECONDS:-120}"

if [ "${SYNC_SH_DETACHED:-0}" != "1" ]; then
	log_dir=$(dirname "$LOG_FILE")
	mkdir -p "$log_dir"
	nohup env SYNC_SH_DETACHED=1 "$0" "$@" >>"$LOG_FILE" 2>&1 </dev/null &
	exit 0
fi

log_message() {
	printf '[%s] %s\n' "$(date '+%Y-%m-%d %H:%M:%S')" "$1"
}

notify() {
	if command -v notify-send >/dev/null 2>&1; then
		notify-send "$1" "${2:-}"
	fi
}

fail() {
	log_message "ERROR: $1"
	printf 'Error: %s\n' "$1" >&2
	notify "Sync Failed" "$1"
	exit 1
}

git rev-parse --is-inside-work-tree >/dev/null 2>&1 || fail "Run this script from inside a git repository"

git rev-parse --verify "$TARGET_BRANCH" >/dev/null 2>&1 || fail "Branch '$TARGET_BRANCH' does not exist"

if [ -n "$(git status --porcelain)" ]; then
	fail "Working tree is not clean"
fi

if ! git remote get-url upstream >/dev/null 2>&1; then
	git remote add upstream "$UPSTREAM_URL"
fi

log_message "Starting sync for branch '$TARGET_BRANCH'"

if command -v timeout >/dev/null 2>&1; then
	timeout "$SYNC_TIMEOUT_SECONDS" git checkout "$TARGET_BRANCH"
	timeout "$SYNC_TIMEOUT_SECONDS" git pull --no-edit upstream "$TARGET_BRANCH"
	timeout "$SYNC_TIMEOUT_SECONDS" git push origin "$TARGET_BRANCH"
else
	log_message "WARNING: timeout command not found; running without enforced timeout"
	git checkout "$TARGET_BRANCH"
	git pull --no-edit upstream "$TARGET_BRANCH"
	git push origin "$TARGET_BRANCH"
fi

log_message "Sync completed successfully"
notify "Sync Done" "Fork synced from upstream"

# exec --no-startup-id /home/i3/git-temp/PCC-CS391/sync.sh