import os
import glob

files = glob.glob('/home/phantom/Documents/Codes/Aetheris/IoT/Learn/web/exp*.html')
for f in files:
    with open(f, 'r') as file:
        content = file.read()
    
    content = content.replace('<a href="index.html" class="home-fab" title="Back to Index">⌂</a>\n', '')
    content = content.replace('<a href="index.html" class="home-fab" title="Back to Index">⌂</a>', '')
    
    with open(f, 'w') as file:
        file.write(content)
print("Done")
