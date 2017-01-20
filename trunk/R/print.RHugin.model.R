print.RHugin.model <- function(x, ...)
{
  empty <- nchar(x$Expression) == 0
  x$Expression[empty] <- "  <<empty expression>>"
  x$Expression[!empty] <- paste("  ", x$Expression[!empty], sep = "")

  if(!is.null(header <- attr(x, "header")))
    cat(header)

  print.data.frame(x, ...)
}


