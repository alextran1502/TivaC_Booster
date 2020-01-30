WORKSPACE=$(pwd)
ARCH=$(uname)

echo $ARCH
if ["$ARCH" == "Darwin"]; then
    echo MAC
else 
    echo Windows
fi