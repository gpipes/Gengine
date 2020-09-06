;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

((dired-mode
  (compile-command . "cd build && cmake --build . && cd ./test/ && Debug\\GengineTest.exe")))
