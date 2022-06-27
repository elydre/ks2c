$version = (((cat .\version_history.md)[-1] -split "\| \[")[1] -split "\]")[0]
git add -A
git commit -m $version -m "statut: $((((cat .\version_history.md)[-1] -split " \| ")[-1] -split " ")[1])"
git push
git tag $version
git tag latest
git push --tags
echo "Version $version deployed"
