# apply_updates.ps1 - Moves updated files back to the project
$projectPath = "D:\My Documents\PlatformIO\ESP32\Projects\JellyfishProject"
$updateFolder = "$projectPath\UpdatesFromChatGPT"

# Get all updated files in UpdatesFromChatGPT
$updatedFiles = Get-ChildItem -Path $updateFolder

if ($updatedFiles.Count -eq 0) {
    Write-Host "⚠️ No updated files found in $updateFolder."
    exit
}

foreach ($file in $updatedFiles) {
    $originalPath = (Get-Content "$updateFolder\$file" | Select-String -Pattern "// ORIGINAL_PATH: (.*)").Matches.Groups[1].Value

    if ($originalPath -ne "") {
        $destinationPath = Join-Path -Path $projectPath -ChildPath $originalPath
        $destinationDir = Split-Path -Path $destinationPath -Parent

        if (!(Test-Path $destinationDir)) {
            New-Item -ItemType Directory -Path $destinationDir | Out-Null
        }

        Move-Item -Path $file.FullName -Destination $destinationPath -Force
        Write-Host "✅ Moved: $file -> $destinationPath"
    } else {
        Write-Host "⚠️ Skipped: $file (No original path found)"
    }
}

Write-Host "🎉 All updated files have been correctly applied!"
