Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

#fenêtre
$window = New-Object System.Windows.Forms.Form
$window.Text = 'Bonjour'
$window.AutoSize = $true        #wrap to content
$window.Height = 1              #Autosize agrandira la fenêtre
$window.FormBorderStyle = 3     #fenêtre à taille fixe
$window.StartPosition = 'CenterScreen'

#mise en page des boutons
$btnLayout = New-Object System.Windows.Forms.FlowLayoutPanel
$btnLayout.AutoSize = $true
$btnLayout.Anchor = 8 #Right

$sayHelloButton = New-Object System.Windows.Forms.Button
$sayHelloButton.Text = 'Dire bonjour'
$btnLayout.Controls.Add($sayHelloButton);

#onclick
$sayHelloButton.Add_Click(
        {    
            $version = (((cat .\version_history.md)[-1] -split "\| \[")[1] -split "\]")[0]
            echo "version: $version"
            git add -A
            git commit -m "$version"
            git push
        }
    )

#ajoute les groupes
$window.Controls.Add($btnLayout);

#montre la fenêtre
$window.ShowDialog()
