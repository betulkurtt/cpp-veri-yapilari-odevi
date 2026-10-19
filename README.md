# C++ Veri Yapıları Ödevi

Bu proje, Veri Yapıları dersi kapsamında hazırlanmış bir C++ ödevidir.

## İçerik

- AVL ağaçları
- Yığın (Stack) veri yapısı
- Bağlı liste tabanlı uygulama
- `Veri.txt` dosyasından veri okuma

## Derleme ve çalıştırma

Windows PowerShell üzerinde proje klasöründe:

```powershell
g++ -Iinclude -Wall -Wextra -pedantic src/main.cpp src/Stack.cpp src/AVLTree.cpp src/Forest.cpp -o bin/Odev2.exe
.\bin\Odev2.exe
```

`Veri.txt` dosyasının proje ana dizininde bulunması gerekir.
