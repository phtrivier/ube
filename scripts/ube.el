(global-set-key [(control ?c) (control ?j)] 'compile-all-or-recompile)

(defconst ube-dir "~/prj/ube")

(defun ube-compile (what)
  (let ((folder (concat ube-dir "/builds/linux/current/src/" what)))
    (set 'compilation-directory folder)
    (set 'compile-command (concat "make -C " folder " check"))
    (compile-or-recompile)))

(defun ube-compile-common ()
  (interactive)
  (ube-compile "common"))

(defun ube-compile-client ()
  (interactive)
  (ube-compile "client"))

(defun ube-compile-mvc ()
  (interactive)
  (ube-compile "mvc"))

(defun ube-compile-engine ()
  (interactive)
  (ube-compile "engine"))

(defun make-folder (what)
  (concat ube-dir "/builds/linux/current/src/" what))

(defun ube-compile-all ()
  (interactive)
  (let ((folder1 (make-folder "common"))
        (folder2 (make-folder "engine"))
	(folder3 (make-folder "mvc"))
	(folder4 (make-folder "client")))
    (set 'compilation-directory folder1)
    (set 'compile-command (concat "make -C" folder1 
				  " check && make -C " folder2 
				  " check && make -C " folder3 
				  " check && make -C " folder4
				  " check" "&& make -C " (make-folder "../") " install" ))
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
			    :file "~/prj/ube/README.textile"
                            :directory "~/prj/ube"
			    :include-path '("/include"
					    "/src"
					    "/src/common"
					    "/src/client"
					    "/src/engine")
			    :system-include-path '("/usr/include/c++/4.4.1" "/usr/include/SDL")))

                            ;; :local-variables (list
                            ;;                   (cons 'compile-command
			    ;; 			    (concat
			    ;; 			     "make -C ~/prj/ube/builds/linux/current/src/engine check"
			    ;; 			     " && "
			    ;; 			     "make -C ~/prj/ube/builds/linux/current/src/client check")))))

(provide 'ube)