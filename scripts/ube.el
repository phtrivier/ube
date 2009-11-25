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

(global-set-key [(control ?c) (control ?j)] 'recompile)

(set (make-local-variable 'compile-command)
     "cd ~/prj/ube/builds/linux/current ; make check")

(set 'compilation-directory "~/prj/ube/builds/linux/current/src/client")

(defun ube-compile (what)
  (let ((folder (concat "~/prj/ube/builds/linux/current/src/" what)))
    (set 'compilation-directory folder)
    (set 'compile-command (concat "make -C " folder " check"))
    (recompile)))

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
  (let ((folder1 (make-folder "engine"))
	(folder2 (make-folder "client")))
    (set 'compilation-directory folder1)
    (set 'compile-command (concat "make -C " folder1 " check && make -C " folder2 " check"))
    (recompile)))
  

(setq ube-project
      (ede-cpp-root-project "ube"
			    :name "ube-pht"
			    :version "0.1.0"
			    :file "~/prj/ube/README.txt"
                            :directory "~/prj/ube"
			    :include-path '("/include"
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