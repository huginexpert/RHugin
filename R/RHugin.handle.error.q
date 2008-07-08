RHugin.handle.error <- function(status)
{
  if(missing(status))
    status <- error.code()

  if(any(status != 0))
    stop(error.description(status)$description, call. = FALSE)

  invisible(NULL)
}


