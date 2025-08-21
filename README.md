<picture>
  <source media="(prefers-color-scheme: dark)" srcset="./.github/assets/logo.svg">
  <img alt="Vultra Logo" src="./.github/assets/logo-light.svg" width="100px" align="left">
</picture>

### `Vultra`

[![License][license-badge]][license-link]
<!-- TODO: [![CI Build][ci-badge]][ci-link]-->

A playful Vulkan rendering library, crafted for a simpler world. 🍃

<div flex="true">
  <a href="#">
    Documentation
  </a>
</div>

## Introduction

`Vultra` aims to empower you to build and prototype games and vulkan apps quickly. It is a lightweight rendering library written in C99, drawing inspiration from the simplicity of [Raylib](https://github.com/raysan5/raylib) and the robustness of [liblava](https://github.com/liblava/liblava). Originally a study project, the focus is on keeping the code clear, simple, and easy to work with.

<details open>
<summary>
 Screenshots
</summary> <br />

</details>

## Usage

> [!CAUTION]
> `Vultra` is currently in a highly work-in-progress state. The API is unstable and subject to significant changes. It is intended for learning and experimentation purposes.

To get started with, here's a simple example that demonstrates the basics:

```c
#include "vultra/vultra.h"

int
main( void )
{
    const int screenWidth  = 640;
    const int screenHeight = 480;

    InitWindow( screenWidth, screenHeight, "Vultra: Basic Window" );
    SetTargetFPS( 60 );

    while( !ShouldQuit() )
        {
            if( IsKeyDown( KEY_ESCAPE ) ) break;

            BeginDrawing();
            {
                // ...
            }
            EndDrawing();
        }

    CloseWindow();
    return EXIT_SUCCESS;
}
```

## Build & Run

##### CPM.cmake

1. First, set up [CPM.cmake] in your project:

   ```bash
   mkdir -p cmake
   wget -O cmake/CPM.cmake https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake
   ```

2. In your `CMakeLists.txt`, add the following lines after `project(...)`:

   ```cmake
   include(cmake/CPM.cmake)

   CPMAddPackage("gh:SOHNE/Vultra@25.0.0")

   add_executable(your_target main.cpp)
   target_link_libraries(your_target PRIVATE Vultra::Vultra)

## Contributing

The majority of Vultra code is open-source. We are committed to a transparent development process and highly appreciate any contributions. Whether you are helping us fix bugs, proposing new features, improving our documentation or spreading the word - we would love to have you as a part of the SOHNE/Vultra community. Please refer to our [contribution guidelines](./CONTRIBUTING.md).

- Bug Report: If you see an error message or encounter an issue while using Vultra, please create a [bug report](https://github.com/SOHNE/Vultra/issues/new?assignees=&labels=type%3A+bug&template=bug.yaml&title=%F0%9F%90%9B+Bug+Report%3A+).

- Feature Request: If you have an idea or if there is a capability that is missing and would make development easier and more robust, please submit a [feature request](https://github.com/SOHNE/Vultra/issues/new?assignees=&labels=type%3A+feature+request&template=feature.yml).

- Documentation Request: If you're reading the Vultra docs and feel like you're missing something, please submit a [documentation request](https://github.com/SOHNE/Vultra/issues/new?assignees=&labels=type%3A+docs&template=documentation-request.yaml&title=%F0%9F%93%96+Documentation%3A+).

## License

**Vultra** is licensed under the [zlib/libpng license](https://opensource.org/licenses/zlib).

You are free to use, modify, and distribute this library under the following conditions:

1.  **No Misrepresentation:** You must not misrepresent the origin of the software. If you use this software in a product, an acknowledgment in the product documentation is appreciated but not required.
2.  **Modified Versions:** Altered source versions must be clearly marked as such and must not be misrepresented as the original software.
3.  **License Notice:** This license notice may not be removed or altered from any source distribution.

For the full license text, please see the [LICENSE](./LICENSE) file.

Vultra depends on several third-party libraries and dependencies, each distributed under its own license. It is the responsibility of the user to review and comply with these additional licenses.

---

[//]: (Externals)

[license-badge]: https://img.shields.io/github/license/SOHNE/Vultra
[license-link]: https://github.com/SOHNE/Vultra/blob/main/LICENSE

[ci-badge]: https://github.com/SOHNE/Vultra/actions/workflows/build.yml/badge.svg
[ci-link]: https://github.com/SOHNE/Vultra/actions/workflows/build.yml

[CPM.cmake]: https://github.com/cpm-cmake/CPM.cmake/
[CMake]: https://cmake.org/

[//]: (EOF)

