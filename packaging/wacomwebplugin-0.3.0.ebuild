# Copyright 1999-2013 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI="5"

inherit nsplugins

DESCRIPTION="An implementation of the Wacom Tablet Plugin, on Linux."
HOMEPAGE="https://github.com/ZaneA/WacomWebPlugin"
SRC_URI="https://github.com/ZaneA/WacomWebPlugin/archive/v${PV}.tar.gz -> ${P}.tar.gz"

LICENSE="GPL-3"
SLOT="0"
KEYWORDS="~amd64 ~x86"
IUSE=""

RDEPEND="
	x11-libs/libX11
	x11-libs/libXi"

DEPEND="${RDEPEND}
	|| ( net-misc/npapi-sdk www-client/firefox[-minimal] )"

S="${WORKDIR}/WacomWebPlugin-${PV}"

src_install() {
	exeinto /usr/$(get_libdir)/${PLUGINS_DIR}
	doexe npWacomWebPlugin.so
}
