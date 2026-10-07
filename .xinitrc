xrdb ~/.Xresources
xwallpaper --zoom ~/dotfilesdwm/Wallpapers/g5op.jpg

exec dbus-run-session sh -c '
    slstatus &
    dunst &
    clipmenud &
    pipewire &
    exec dwm
'
