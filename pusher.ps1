$version = (((cat .\version_history.md)[-1] -split "\| \[")[1] -split "\]")[0]
git add -A
git commit -m $version -m "statut: $((((cat .\version_history.md)[-1] -split " \| ")[-1] -split " ")[1])"
git push

if ($(git tag $version) -like "*fatal*") {
    echo "le tag $version existe, suppression..."
    git tag -d $version
    git push --delete origin $version
}

git push --tags

echo "Version $version deployed"
