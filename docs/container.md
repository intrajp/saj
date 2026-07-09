# Container usage

This repository can build a container image that installs `saj` and
`cmp-saj` from the current source tree.

## Build

```sh
docker build -t saj:dev .
```

Podman can be used with the same arguments:

```sh
podman build -t saj:dev .
```

## Run

Mount a sosreport directory read-only at `/data` and pass that path to `saj`
with `-D`.

```sh
docker run --rm -it -v /path/to/sosreport:/data:ro saj:dev -D /data
```

With Podman:

```sh
podman run --rm -it -v /path/to/sosreport:/data:ro,Z saj:dev -D /data
```

The image entrypoint is `saj`, so any arguments after the image name are passed
directly to the program.

## Configuration

The container includes the default configuration installed by `make install`.
`saj` reads the user configuration from `~/.saj/saj.conf`; the image runs as
root by default, so mount custom configuration files under `/root/.saj`.

```sh
docker run --rm \
  -it \
  -v /path/to/saj-config-dir:/root/.saj:ro \
  -v /path/to/sosreport:/data:ro \
  saj:dev -D /data
```

For rootless Podman on SELinux systems, add `:Z` to bind mounts that the
container must read or write.

## Troubleshooting

If `saj` reaches `analyzing sar files.` even when sar entries are commented in
`saj.conf`, this is expected with the current implementation. The sosreport file
collection is controlled by `saj.conf`, but the final sar analyzer runs when
`var/log/sa` exists under the analyzed sosreport directory.

For a container smoke test that skips sar analysis, temporarily hide that
directory in the extracted sosreport:

```sh
mv /path/to/sosreport/var/log/sa /path/to/sosreport/var/log/sa.disabled
```

Restore it after the test if needed:

```sh
mv /path/to/sosreport/var/log/sa.disabled /path/to/sosreport/var/log/sa
```
