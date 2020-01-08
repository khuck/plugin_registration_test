! main.F90
! --------
! This program tests the plugin API from a fortran program.

      program main
        print *, "main_fortran"
        call plugin_init()
        call plugin_function()
        call plugin_finalize()
      end