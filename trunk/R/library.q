.First.lib <- function(libname, pkgname)
{
  if(Sys.info()["sysname"] == "Windows") {
    path <- Sys.getenv("PATH")
    if(length(grep("HDE6.7C", path)) == 0) {
      HuginVersions <- c("Hugin Researcher 6.9", "Hugin Lite 6.9")
      HuginDllPaths <- paste(Sys.getenv("PROGRAMFILES"),
                            "Hugin Expert",
                             HuginVersions,
                            "HDE6.7C\\Lib\\VC8\\Release\\hugin2-6.7-vc8.dll",
                             sep = "\\")

      if(length(HuginVersion <- which(file.exists(HuginDllPaths)))) {
        HuginVersion <- HuginVersions[HuginVersion[1]]
        HuginPath <- paste(Sys.getenv("PROGRAMFILES"),
                          "Hugin Expert",
                           HuginVersion,
                          "HDE6.7C\\Lib\\VC8\\Release",
                           sep = "\\")

        Sys.setenv(PATH = paste(path, HuginPath, sep= ";"))
      }

      else {
        detach("package:RHugin")
        stop("auto-detection of Hugin failed", "\n",
             "add the folder containing the file ",
              dQuote("hugin2-6.7-vc8.dll"),
             " to the Windows path")
      }
    }
  }

  library.dynam("RHugin")
  invisible(NULL)
}


