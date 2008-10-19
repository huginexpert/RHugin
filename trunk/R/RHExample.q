RHExample <- function(topic) 
{
  paths <- .find.package("RHugin", NULL, verbose = FALSE)
  paths <- paths[file_test("-d", file.path(paths, "demo"))]

  available <- character(0)
  paths <- file.path(paths, "demo")

  for(p in paths) {
    files <- basename(tools::list_files_with_type(p, "demo"))
    files <- files[topic == tools::file_path_sans_ext(files)]

    if(length(files) > 0) 
      available <- c(available, file.path(p, files))
  }

  if(length(available) == 0) 
    stop(gettextf("No example found for topic '%s'", topic), domain = NA)

  if(length(available) > 1)
    available <- available[1]

  source(available, echo = FALSE, verbose = FALSE)
}


