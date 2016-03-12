# Maintainer: gilzoide <gilzoide@gmail.com>

pkgname=lap-git
pkgver=0.1.0
pkgrel=1
pkgdesc="A functional style C++11 library for parsing command line arguments"
arch=('i686' 'x86_64')
url="https://github.com/gilzoide/lap"
license=("GPL3")
depends=()
makedepends=('git' 'scons')
source=("$pkgname"::'git://github.com/gilzoide/lap.git')
md5sums=('SKIP')

# functions
pkgver () {
	cd "$pkgname"
	git log -n 1 --date=short | awk '/Date/ {gsub ("-",""); print $2}'
}

build () {
	cd "$pkgname"
	scons
}

package () {
	cd "$pkgname"
	scons install --prefix "${pkgdir}"
}
