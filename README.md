# EmberdawnIrrlicht version 1.9

The Irrlicht Engine is an open source realtime 3D engine written in C++.

This is a fork by the [Emberdawn](https://github.com/emberdawn-game) developers that contains features, customizations and fixes specifically for use in Emberdawn. Based on IrrlichtMt by the [Minetest](https://github.com/minetest) team.

## Build

The build system is CMake, and vcpkg is used to manage dependencies.

We recommend you set the environment variable `VCPKG_ROOT` to the path where vcpkg is installed. In this case the build system will find and use vcpkg automatically.

Otherwise, you will need to set the CMake variable `CMAKE_TOOLCHAIN_FILE` to point to the CMake toolchain file provided by vcpkg. For example, `cmake . -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake`.

Most dependencies will be downloaded and built automatically by vcpkg. The following dependencies must be provided by the system:

 * OpenGL or OpenGL ES
 * On Unix: X11

On Windows OpenGL headers and libraries are bundled with Visual Studio.

On a Linux system you might build like this:

```bash
git clone git@github.com:emberdawn-game/emberdawn-irrlicht
cd emberdawn-irrlicht
cmake .
make
```

## Platforms

The following platforms are officially supported:

 * Windows (compiling with MSVC)
 * Linux/X11 (compiling with gcc or clang)
 * macOS (compiling with clang)

Other platforms or compilers may work too, and if not we accept patches.

## License

The license of the Irrlicht Engine is based on the zlib/libpng license and applies to this fork, too.

> ### The Irrlicht Engine License
>
> Copyright (C) 2002-2012 Nikolaus Gebhardt
>
> This software is provided 'as-is', without any express or implied
> warranty.  In no event will the authors be held liable for any damages
> arising from the use of this software.
>
> Permission is granted to anyone to use this software for any purpose,
> including commercial applications, and to alter it and redistribute it
> freely, subject to the following restrictions:
>
> 1. The origin of this software must not be misrepresented; you must not
>    claim that you wrote the original software. If you use this software
>    in a product, an acknowledgement in the product documentation would be
>    appreciated but is not required.
> 2. Altered source versions must be clearly marked as such, and must not be
>    misrepresented as being the original software.
> 3. This notice may not be removed or altered from any source distribution.
