FROM fedora:latest AS build

RUN dnf -y install \
    autoconf \
    automake \
    gcc-c++ \
    gettext-devel \
    glibc-langpack-ja \
    intltool \
    libtool \
    make \
    which \
 && dnf clean all

ENV LANG=ja_JP.UTF-8
ENV LC_ALL=ja_JP.UTF-8

WORKDIR /src/saj

COPY . .

RUN sh ./autogen.sh \
 && ./configure \
 && make \
 && make install DESTDIR=/opt/saj-root

FROM fedora:latest

RUN dnf -y install glibc-langpack-ja libgcc \
 && dnf clean all

ENV LANG=ja_JP.UTF-8
ENV LC_ALL=ja_JP.UTF-8

COPY --from=build /opt/saj-root/ /

RUN ldconfig \
 && mkdir -p /data /work

WORKDIR /work

ENTRYPOINT ["saj"]
CMD ["--help"]
