.First.lib <- function(libname, pkgname)
{
  if(Sys.info()["sysname"] == "Windows") {
    path <- Sys.getenv("PATH")
    if(length(grep("HDE6.7C", path)) == 0) {
      path <- paste(path, "C:\\Program Files\\Hugin Expert\\Hugin Researcher 6.9\\HDE6.7C\\Lib\\VC6\\Release", sep = ";")
      Sys.setenv(PATH = path)
    }
  }

  library.dynam("RHugin")

  invisible(NULL)
}

