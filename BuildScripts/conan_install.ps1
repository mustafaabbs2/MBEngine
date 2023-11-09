param($config)

$ErrorActionPreference = "Stop"


#Use a conan .txt file if you want some simple dependencies..
# Write-Host "Installing build tools..."
# conan install $PSScriptRoot/conanfileBuildTools.txt --profile $PSScriptRoot/Windows/conanprofile.txt -if $PSScriptRoot/../build/BuildTools; if ($LASTEXITCODE -ne 0) { Exit $LASTEXITCODE }

Write-Host "Installing Conan dependencies..."

if ($config -eq "Debug")
{
    conan install $PSScriptRoot/../conanfile.py --profile $PSScriptRoot/Windows/conanprofiledebug.txt -if $PSScriptRoot/../build/Debug; if ($LASTEXITCODE -ne 0) { Exit $LASTEXITCODE }
}
else
{
    conan install $PSScriptRoot/../conanfile.py --profile $PSScriptRoot/Windows/conanprofile.txt -if $PSScriptRoot/../build/Release; if ($LASTEXITCODE -ne 0) { Exit $LASTEXITCODE }
}

exit $LASTEXITCODE
