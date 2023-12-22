version=$(tail -n 1 version_history.md | awk -F ' \\| ' '{print $2}' | awk -F ']' '{print $1}')
git add -A
git commit -m "$version" -m "statut: $(tail -n 1 version_history.md | awk -F ' \\| ' '{print $NF}' | awk '{print $1}')"
git push

git tag "$version"

if [ $? -eq 0 ]; then
    echo "tag $version already exists"
    git tag -d "$version"
    git push --delete origin "$version"
    git tag "$version"
fi

git push --tags

echo "version $version pushed"
