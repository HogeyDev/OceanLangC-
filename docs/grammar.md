$$
\begin{align}

      [\text{Program}] &\to [\text{Scope}] \\
      [\text{Scope}] &\to [\text{Statement}]^* \\
      [\text{Statement}] &\to
      \begin{cases}
            [\text{VariableAssignment}] \\
            [\text{FunctionDeclaration}] \\
            [\text{FunctionCall}] \\
      \end{cases} \\
      [\text{VariableAssignment}] &\to \text{type identifier = [Expression]} \\
      [\text{Expression}] &\to
      \begin{cases}
            [\text{Term}] \\
            [\text{BinaryExpression}]
      \end{cases} \\
      [\text{Term}] &\to
      \begin{cases}
            \text{integer\textunderscore literal} \\
            \text{identifier} \\
            \text{string} \\
            [\text{Expression}]
      \end{cases} \\
      [\text{BinaryExpression}] &\to
      \begin{cases}
            [\text{Expression}] + [\text{Expression}] & \text{precedence = 0} \\
            [\text{Expression}] - [\text{Expression}] & \text{precedence = 0} \\
            [\text{Expression}] \div [\text{Expression}] & \text{precedence = 1} \\
            [\text{Expression}] \times [\text{Expression}] & \text{precedence = 1}
      \end{cases} \\
      [\text{FunctionDeclaration}] &\to \text{type identifier() [\text{Scope}]} \\
      [\text{FunctionCall}] &\to \text{identifier}()
\end{align}
$$