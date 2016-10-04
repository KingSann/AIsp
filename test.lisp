(defvar MAP 
    (list (list 0 0 0 0) 
          (list 0 0 0 0) 
          (list 0 0 0 0) 
          (list 0 0 0 0)))

;; 移动方向
(defvar MOVE_UP     0)
(defvar MOVE_DOWN   1)
(defvar MOVE_LEFT   2)
(defvar MOVE_RIGHT  3)

(defvar BIGGEST_VALUE 4096)   ;; 合并最大值

(defvar SCORE       0)      ;; 当前分数

(defpc gameOver ()          ;; 游戏结束，没有地方放方块
    (exit))

(defpc updateScore (score)      ;; 更新分数
    (exit))

(defun transpose (_map)     ;; 矩阵转置
  (letE ((ret (emList))
      (item_len (len (getItem _map 1))))
    (withRet ret
      (for J 1 item_len 1
        (addItem ret 
          (letE ((tmp (emList)))
            (withRet tmp
              (forEach I _map
                (addItem tmp (getItem I J))))))))))


(defun getUnZero (line)       ;; 获取列表中非零项
    (letE ((ret (emList)))
        (withRet ret
            (forEach I line
                (cond 
                  ((!= I 0) 
                    (addItem ret I)))))))


(defun fillZero (tot)         ;; 返回由若干个0组成的列表
    (letE ((ret (emList)))
        (withRet ret 
            (for I 1 tot 1
                (addItem ret 0)))))

(defun reverse (line)       ;; 翻转一行
    (letE ((ret (emList))
           (leng (len line)))
        (withRet ret
            (for I leng 1 (neg 1)
                (addItem ret (getItem line I))))))

(defun combine (_line)      ;; 合并
    (letE ((leng (len line))
         (line (copy _line)))
        (if (>= leng 3)
          (withRet line
              (cond 
                ((and (= (getItem line 1) (getItem line 2)) (!= (getItem line 1) BIGGEST_VALUE))
                    (del 1 line)
                    (del 1 line)
                    (insert line 1 (* (getItem line 1) 2))
                      (set SCORE (+ SCORE (* (getItem line 1) 2)))
                      (callp updateScore SCORE))
                  (#t
                    (del 1 line)
                    (insert line 1 (getItem line 1)))))
            line)))

(defun merge (line)         ;; 合并一行
    (letE ((merged (callf combine (callf getUnZero (copy line)))))
        (withRet merged 
            (append (callf fillZero (- (len line) (len merged))) merged))))

(defun map_merge (_map)       ;; 将输入数组每个元素依次merge最后返回结果
    (letE ((ret (emList)))
        (withRet ret
            (forEach I _map
                (addItem ret (callf merge I))))))


(defun map_rev_mer_rev (_map)
  (letE ((ret (emList)))
        (withRet ret
            (forEach I _map
                (addItem ret (callf reverse 
                        (callf merge 
                          (callf reverse I))))))))

(defun move (type)            ;; 移动
    (cond ((= type MOVE_UP)     (callf transpose (callf transpose (callf move MOVE_LEFT)))    )
          ((= type MOVE_DOWN)   (callf transpose (callf transpose (callf move MOVE_LEFT)))    )
          ((= type MOVE_LEFT)   (callf map_merge MAP)                                         )
          ((= type MOVE_RIGHT)  (callf map_rev_mer_rev MAP)                                   )))


(defpc doMove (type)      ;; 移动
  (letS ((moved (callf move type))
       (same  #t))
    (for I 1 (len moved) 1
      (cond ((!= (getItem MAP I) (getItem moved I))
          (set same #f))))
    (cond ((not same)
        (set MAP moved)
        (callp newBlock)))))

(defpc newBlock ()            ;; 新建一个块
    (letS ((zero 0))
        (forEach I MAP 
            (forEach J I
                (cond ((= J 0)
                        (set zero (+ zero 1))))))  ;; 检查有多少个零
        (cond ((= zero 0) (callp gameOver))
              (#t 
                (letS ((pos (callf rand 1 zero)
                       (tot 0))
                        (forEach I MAP 
                            (forEach J I
                                (cond ((= J 0) 
                                  (set tot (+ tot 1))))
                                (cond ((= tot pos) 
                                  (set J 
                                    (if (<= (randRange 1 10) 2)   ;; 20%几率产生‘4’块
                                      4 
                                      2))))))))))))

(defpc init ()          ;; 初始化
  (setRandSeed 1)       ;; 初始化随即种子
  (set MAP          ;; 初始化地图
    (list (list 0 0 0 0) 
              (list 0 0 0 0) 
              (list 0 0 0 0) 
              (list 0 0 0 0)))
  (set SCORE 0)
  (callp updateScore SCORE))


(defpc newGame ()       ;; 开始新游戏
  (set MAP          ;; 初始化地图
    (list (list 0 0 0 0) 
              (list 0 0 0 0) 
              (list 0 0 0 0) 
              (list 0 0 0 0)))
  (callp newBlock)
  (set SCORE 0)
  (callp updateScore SCORE))