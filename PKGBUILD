# Maintainer: Allan McRae <allan@archlinux.org>

pkgname=mbpfan
pkgver=1.1
pkgrel=1
pkgdesc="Automatically adjust the fan on a MacBook Pro"
arch=('i686' 'x86_64')
license=('GPL3')
source=(mbpfan.c 
        mbpfan.rc)

md5sums=('57be3248ffa6563f06435f0b3b3451f5'
         '6b58ce23ade4c2ccb8cadc004bb9e172')

build() {
  cd $srcdir/
  gcc -o mbpfan -lm -Wall $CFLAGS $LDFLAGS mbpfan.c
}

package() {
  install -Dm755 $srcdir/mbpfan $pkgdir/usr/bin/mbpfan
  install -Dm755 $srcdir/mbpfan.rc $pkgdir/etc/rc.d/mbpfan
}
