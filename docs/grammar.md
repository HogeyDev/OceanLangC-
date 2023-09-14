<!-- Prog -> Stmt*

Stmt -> exit
      | Expr
      | let ident = Expr;

Expr -> Term
      | BinExpr

BinExpr -> Expr * Expr
         | Expr / Expr
         | Expr + Expr
         | Expr - Expr

Term -> int_lit
      | ident -->

$$
\begin{align}

[\text{Program}] \to [\text{Compound}] \\
[\text{Compound}] \to [\text{Statement}]^* \\


\end{align}
$$