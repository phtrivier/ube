(defun file-name ()
  (let ((tokens (split-string (buffer-name) "\\.")))
    (car tokens)))

(defun class-name-elements ()
  (split-string (file-name) "_"))

(defun class-name ()
  (mapconcat 'capitalize (class-name-elements) ""))
    
(defun class-define-clause ()
  (concat "_" (mapconcat 'upcase (class-name-elements) "_") "_HPP_"))

(define-skeleton class-header-file
  "Insert the beginning of a class header file"
  "Describe the class : "
  "#ifndef " (class-define-clause) "\n"
  "#define " (class-define-clause) "\n"
  "\n"
  "\n"
  "/**\n"
  " * " str "\n"
  " */\n"
  "class " (class-name) " { \n"
  _
  "\n"
  "public:\n"
  "};\n"
  "\n"
  "#endif // " (class-define-clause) "\n")

(define-skeleton gmock-test
  "Insert an empty Gmock Test skeleton"
  "Header file : "
  "#include \"" str "\"\n"
  "#include <gtest/gtest.h>\n"
  "#include <gmock/gmock.h>\n"
  "#include <stdexcept>\n"
  "using namespace std;\n"
  "\n"
  "namespace {\n"
  "  class " (class-name) " : public ::testing::Test {\n"
  "  protected:\n"
  "    " (class-name) "() {\n"
  "    }\n"
  "\n"
  "    virtual ~" (class-name) "() {\n"
  "    }\n"
  "\n"
  "    virtual void SetUp() {\n"
  "    }\n"
  "\n"
  "    virtual void TearDown() {\n"
  "    }\n"
  "\n"
  "  };\n"
  "\n"
  "  TEST_F(" (class-name) ", DoesSomethingCool) {\n"
  "    " _ "\n"
  "  }\n"
  "\n"
  "} // Namespace\n")

(define-skeleton gtest-f
  "Includes a TEST_F macro"
  "Test name : "
  "TEST_F(" (class-name) ", " str ") {\n"
  "    " _ "\n"
  "  }\n")

(define-skeleton method-comments
  "Include empty method comments"
  ""
  "/**\n"
  "   * " _ "\n"
  "   */")

(define-skeleton cpp-prevent-copying
  "Include empty copy-constructor and equal operator"
  ""
  "  // Prevents copying of the class\n"
  "  " (class-name) "(const " (class-name) " & other) { } \n"
  "  " (class-name) " & operator = (const " (class-name) " & other) { } \n")

(global-set-key [(control ?c) (control ?j)] 'compile-all-or-recompile)

(defun ube-compile (what)
  (let ((folder (concat "~/prj/ube/builds/linux/current/src/" what)))
    (set 'compilation-directory folder)
    (set 'compile-command (concat "make -C " folder " check"))
    (compile-or-recompile)))

(defun ube-compile-common ()
  (interactive)
  (ube-compile "common"))

(defun ube-compile-client ()
  (interactive)
  (ube-compile "client"))


(defun ube-compile-engine ()
  (interactive)
  (ube-compile "engine"))

(defun make-folder (what)
  (concat "~/prj/ube/builds/linux/current/src/" what))

(defun ube-compile-all ()
  (interactive)
  (let ((folder1 (make-folder "common"))
        (folder2 (make-folder "engine"))
	(folder3 (make-folder "client")))
    (set 'compilation-directory folder1)
    (set 'compile-command (concat "make -C" folder1 " check && make -C " folder2 " check && make -C " folder3 " check" "&& make -C " (make-folder "") " install" ))
    (compile-or-recompile)))

(defun compile-or-recompile ()
  (interactive)
  (if (fboundp 'recompile)
      (recompile)
    (compile compile-command)))

(defun compile-all-or-recompile ()
  (interactive)
  (if (fboundp 'recompile)
      (recompile)
    (ube-compile-all)))

(setq ube-project
      (ede-cpp-root-project "ube"
			    :name "ube-pht"
			    :version "0.1.0"
			    :file "~/prj/ube/README.txt"
                            :directory "~/prj/ube"
			    :include-path '("/include"
					    "/src"
					    "/src/common"
					    "/src/client"
					    "/src/engine")
			    :system-include-path '("/usr/include/c++/4.4.1")))

                            ;; :local-variables (list
                            ;;                   (cons 'compile-command
			    ;; 			    (concat
			    ;; 			     "make -C ~/prj/ube/builds/linux/current/src/engine check"
			    ;; 			     " && "
			    ;; 			     "make -C ~/prj/ube/builds/linux/current/src/client check")))))

(provide 'ube)