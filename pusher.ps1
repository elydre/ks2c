Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

#fenêtre
$window = New-Object System.Windows.Forms.Form
$window.Text = "GUI"
$window.Width = 220
$window.Height = 120
$window.StartPosition = 'CenterScreen'
$window.FormBorderStyle = 3 #fenêtre à taille fixe
$window.Font = New-Object System.Drawing.Font('Arial', 12)
$window.TopMost = $true

# bouton
$Button = New-Object System.Windows.Forms.Button
$Button.Text = 'commit version'

# dimensions du bouton
$Button.Width = 140
$Button.Height = 30

# position du bouton
$Button.Left = 30
$Button.Top = 25

# action du bouton
$Button.Add_Click(
        {    
            $version = (((cat .\version_history.md)[-1] -split "\| \[")[1] -split "\]")[0]
            git add -A
            git commit -m $version
            git push
            $window.Text = "v$version"
        }
    )
# ajout du bouton à la fenêtre
$window.Controls.Add($Button)

# affichage de la fenêtre
$window.ShowDialog()
