error.description <- function(code)
{
  list(
    name = .Call("RHugin_error_name", code, PACKAGE = "RHugin"),
    description = .Call("RHugin_error_description", code, PACKAGE = "RHugin")
  )
}

