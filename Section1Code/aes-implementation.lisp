;;Erwin Hernández García
;;Eron Romero Argumedo 
;;17 de octubre de 2016
;;Ejercicio 1, sección 1

(load "aes32.lisp")
(defun crear-llave (tamaño-llave)
  (let ((array (make-array (/ (nth (1- tamaño-llave)
                                   +aes-key-bits+) 8)
                           :element-type 'unsigned-byte
                           :initial-element 0)))
    (do ((i 0 (1+ i)))
        ((eql i (array-dimension array 0)) array)
      (setf (aref array i) (random #xFF)))))
(defun bin-array->hex-str (bin)
  (let ((hex (make-string (* 2 (length bin)))))
    (dotimes (i (length bin))
      (let ((h (format nil "~2,'0X" (aref bin i))))     
        (setf (char hex (* 2 i)) (char h 0))
        (setf (char hex (1+ (* 2 i))) (char h 1))))
    hex))

(defun obtain-keys ()
  (format t "Bienvenido, Inserte su archivo~%")
  (let* ((file (read))
        (key1 (bin-array->hex-str
               (aes-key-fkey (aes-expand-key (crear-llave 1)))))
        (key2 (bin-array->hex-str
               (aes-key-fkey (aes-expand-key (crear-llave 2)))))
        (key3 (bin-array->hex-str
               (aes-key-fkey (aes-expand-key (crear-llave 3)))))
        (f-stream (open (symbol-name file) :direction :output)))
    (setq function (lambda (limit f-stream string)
                     (do ((i 0 (1+ i)))
                         ((eql i (1+ limit)) (terpri f-stream))
                       (write-line string
                                   f-stream
                                   :start (* i 8)
                                   :end (+ (* i 8) 8)))))
    (write-line "128 bits" f-stream)
    (terpri f-stream)
    (funcall function 10 f-stream key1)
    (write-line "192 bits" f-stream)
    (terpri f-stream)
    (funcall function 12 f-stream key2)
    (write-line "256 bits" f-stream)
    (terpri f-stream)
    (funcall function 14 f-stream key3)
    (close f-stream)))
