# Icinga 2
# Copyright (C) 2012-2018 Icinga Development Team (https://icinga.com)
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation
# Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.

# Install $src into directory $dest - usually only used for config files
#
# * similar to install() a non absolute path is prefixed with CMAKE_INSTALL_PREFIX on runtime
# * in case of CPack path with be prefixed with share/skel/
# * DESTDIR is prefixed as well
#
# also see https://cmake.org/cmake/help/latest/command/install.html
function(install_if_not_exists src dest)
  if(NOT IS_ABSOLUTE "${src}")
    set(src "${CMAKE_CURRENT_SOURCE_DIR}/${src}")
  endif()

  get_filename_component(src_name "${src}" NAME)

  install(CODE "
    set(dest \"${dest}\")

    if (\"\${CMAKE_INSTALL_PREFIX}\" MATCHES .*/_CPack_Packages/.*)
      set(dest \"share/skel/\${dest}\")
      set(force_overwrite TRUE)
    else()
      set(force_overwrite FALSE)
    endif()

    if(NOT IS_ABSOLUTE \"\${dest}\")
      set(dest \"\${CMAKE_INSTALL_PREFIX}/\${dest}\")
    endif()

    set(full_dest \"\$ENV{DESTDIR}\${dest}/${src_name}\")

    if(force_overwrite OR NOT EXISTS \"\${full_dest}\")
      message(STATUS \"Installing: ${src} into \${full_dest}\")

      execute_process(COMMAND \${CMAKE_COMMAND} -E copy \"${src}\" \"\${full_dest}\"
                      RESULT_VARIABLE copy_result
                      ERROR_VARIABLE error_output)
      if(copy_result)
        message(FATAL_ERROR \${error_output})
      endif()
    else()
      message(STATUS \"Skipping  : \${full_dest}\")
    endif()
  ")
endfunction(install_if_not_exists)
