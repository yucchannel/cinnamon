#!/bin/bash

# リモートのバージョン情報を取得
REMOTE_VERSION=$(curl -s https://raw.githubusercontent.com/yucchannel/cinnamon/main/version.txt)
LOCAL_VERSION=$(cat current_version.txt)

# バージョンが異なる場合、アップデートを実行
if [ "$REMOTE_VERSION" != "$LOCAL_VERSION" ]; then
  echo "New version available! Updating from $LOCAL_VERSION to $REMOTE_VERSION..."
  
  # 最新のリポジトリをクローンまたはプル
  git pull origin main
  
  # 新しいバージョンをローカルのcurrent_version.txtに更新
  echo $REMOTE_VERSION > current_version.txt
  
  echo "Update complete!"
else
  echo "You already have the latest version ($LOCAL_VERSION)."
fi
