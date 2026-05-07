#!/usr/bin/env bash

set -euo pipefail

if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
	echo "Error: not inside a git repository."
	exit 1
fi

if [ -z "$(git status --porcelain)" ]; then
	echo "Nothing to commit."
	exit 0
fi

pick_file_from_status() {
	local type="$1"
	if [ "$type" = "new" ]; then
		git status --porcelain | awk '/^\?\? / {print substr($0,4); exit}'
	else
		git status --porcelain | awk '/^ M |^M |^MM |^AM |^RM |^ T |^T / {print substr($0,4); exit}'
	fi
}

get_first_nonempty_line() {
	local file="$1"
	if [ -f "$file" ]; then
		awk 'NF {print; exit}' "$file"
	fi
}

target_file="$(pick_file_from_status new)"
if [ -z "$target_file" ]; then
	target_file="$(pick_file_from_status modified)"
fi

if [ -z "$target_file" ]; then
	echo "No new or modified files found."
	exit 1
fi

first_line="$(get_first_nonempty_line "$target_file")"

if [ -z "${first_line:-}" ]; then
	commit_message="add $target_file"
else
	commit_message="add $first_line"
fi

git add .
git commit -m "$commit_message"
git push

echo "Pushed with commit message: $commit_message"
