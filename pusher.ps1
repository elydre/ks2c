$version = (((cat .\version_history.md)[-1] -split "\| \[")[1] -split "\]")[0]
echo "version: $version"
git add -A
git commit -m "$version"
git push