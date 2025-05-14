#!/usr/bin/env bash
set -e

NUM_BLOCKS=1
OUT_DIR="../var"

while [ $# -gt 0 ]; do
  case "$1" in
    -n)
      NUM_BLOCKS="$2"
      shift 2
      ;;
    -d)
      OUT_DIR="$2"
      shift 2
      ;;
    *)
      echo "Usage: $0 -n <num_blocks> [-d <output_dir>]" >&2
      exit 1
      ;;
  esac
done

mkdir -p "$OUT_DIR"

MERGED="$OUT_DIR/blocks.txt"
echo -n "" > "$MERGED"

latest_info=$(curl -s "https://api.blockcypher.com/v1/btc/main")
latest_height=$(echo "$latest_info" \
  | grep '"height"' \
  | sed 's/.*"height":[ ]*\([0-9]*\),.*/\1/')
  
 start=$(( latest_height - NUM_BLOCKS + 1 ))
 
 for (( h = start; h <= latest_height; h++ )); do
  block_json=$(curl -s "https://api.blockcypher.com/v1/btc/main/blocks/$h")

  hash=$(echo "$block_json" \
    | grep '"hash"' \
    | sed 's/.*"hash":[ ]*"\([^"]*\)".*/\1/')
  total=$(echo "$block_json" \
    | grep '"total"' \
    | sed 's/.*"total":[ ]*\([0-9]*\).*/\1/')
  time=$(echo "$block_json" \
    | grep '"time"' \
    | sed 's/.*"time":[ ]*"\([^"]*\)".*/\1/')
  relayed_by=$(echo "$block_json" \
    | grep '"relayed_by"' \
    | sed 's/.*"relayed_by":[ ]*"\([^"]*\)".*/\1/')
  prev_block=$(echo "$block_json" \
    | grep '"prev_block"' \
    | sed 's/.*"prev_block":[ ]*"\([^"]*\)".*/\1/')
    received_time=$(date -u +'%Y-%m-%dT%H:%M:%SZ')
    {
    echo "hash: $hash"
    echo "height: $h"
    echo "total: $total"
    echo "time: $time"
    echo "received_time: $received_time"
    echo "relayed_by: $relayed_by"
    echo "prev_block: $prev_block"
  } >> "$MERGED"
  echo "" >> "$MERGED"
  
  done
