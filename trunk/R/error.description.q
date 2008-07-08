error.description <- function(code)
{
  error <- list()
  error$name <- .Call("RHugin_error_name", as.integer(code),
                       PACKAGE = "RHugin")
  error$description <- .Call("RHugin_error_description", as.integer(code),
                              PACKAGE = "RHugin")
  error
}

