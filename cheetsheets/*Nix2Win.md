# *Nix to Win

## bash to powershell

> [ref 1](https://virtualizationreview.com/articles/2020/07/27/bash-powershell-cheat-sheet.aspx)
>
> [ref 2](https://blog.ironmansoftware.com/daily-powershell/bash-powershell-cheatsheet/)

echo Write-Host

| bash |                pwsh                 |
| :--: | :---------------------------------: |
| echo |       Write-Host/Write-Output       |
| grep |             Get-String              |
|  Cd  |          Set-Location(cd)           |
|  Cp  |            Copy-Item(cp)            |
| Kill |            Stop-Process             |
|  Ls  |          Get-ChildItem(ls)          |
|  Ps  |             Get-Process             |
| pwd  |          Get-Location(pwd)          |
|  Rm  | Remove-Item(Rm, ri, rmdir, rd, del) |