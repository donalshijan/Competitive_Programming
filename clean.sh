#!/bin/bash

echo "🧹 Cleaning up *.txt and *.out files in the current directory..."
rm -v ./*.txt ./*.out 2>/dev/null
echo "✅ Cleanup complete."
