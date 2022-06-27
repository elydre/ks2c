Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

#fenêtre
$window = New-Object System.Windows.Forms.Form
$window.Text = "GUI"
$window.Width = 220
$window.Height = 120
$window.StartPosition = 'CenterScreen'


$sayHelloButton = New-Object System.Windows.Forms.Button
$sayHelloButton.Text = 'commit version'
# dimensions du bouton
$sayHelloButton.Width = 100
$sayHelloButton.Height = 30
# position du bouton
$sayHelloButton.Left = 50
$sayHelloButton.Top = 25
# action du bouton
$sayHelloButton.Add_Click(
        {    
            $version = (((cat .\version_history.md)[-1] -split "\| \[")[1] -split "\]")[0]
            echo "version: $version"
            git add -A
            git commit -m "$version"
            git push
            echo "version $version committed"
        }
    )
# ajout du bouton à la fenêtre
$window.Controls.Add($sayHelloButton)
# affichage de la fenêtre
$window.ShowDialog()
