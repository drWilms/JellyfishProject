# sync_files.ps1 - Syncs modified files for ChatGPT
$projectPath = "D:\My Documents\PlatformIO\ESP32\Projects\JellyfishProject"
$syncFolder = "$projectPath\SyncForChatGPT"

# Create SyncForChatGPT if it doesn't exist
if (!(Test-Path $syncFolder)) {
    New-Item -ItemType Directory -Path $syncFolder | Out-Null
}

# Get list of modified files in project
$modifiedFiles = git status --porcelain | ForEach-Object { ($_ -split '\s+')[1] }

# Copy modified files to SyncForChatGPT
foreach ($file in $modifiedFiles) {
    $sourceFile = Join-Path -Path $projectPath -ChildPath $file
    $destinationFile = Join-Path -Path $syncFolder -ChildPath (Split-Path -Leaf $file)

    if (Test-Path $sourceFile) {
        Copy-Item -Path $sourceFile -Destination $destinationFile -Force
        Write-Host "Copied: $file -> $destinationFile"
    }
}

Write-Host "✅ Modified files copied to $syncFolder. Ready for upload."
