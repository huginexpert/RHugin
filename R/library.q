.First.lib <- function(libname, pkgname)
{
  if(Sys.info()["sysname"] == "Windows") {

    path <- Sys.getenv("PATH")

    if(length(grep("HDE7.2C", path)) == 0) {

      HuginVersions <- c("Hugin Researcher 7.2",
                         "Hugin Lite 7.2")

      HuginDllPaths <- paste(Sys.getenv("PROGRAMFILES"),
                            "Hugin Expert",
                             HuginVersions,
                            "HDE7.2C\\Lib\\VC8\\Release\\hugin2-7.2-vc8.dll",
                             sep = "\\")

      if(length(HuginVersion <- which(file.exists(HuginDllPaths)))) {

        HuginVersion <- HuginVersions[HuginVersion[1]]

        HuginPath <- paste(Sys.getenv("PROGRAMFILES"),
                          "Hugin Expert",
                           HuginVersion,
                          "HDE7.2C\\Lib\\VC8\\Release",
                           sep = "\\")

        Sys.setenv(PATH = paste(path, HuginPath, sep= ";"))
      }

      else {
        warning("RHugin did not find Hugin in the expected location")
      }
    }
  }

  else if(Sys.info()["sysname"] == "Darwin") {

    if(nchar(Sys.getenv("HUGINHOME")) == 0) {

      files <- list.files("/Applications")

      if(length(HuginDir <- files[grep("HDE", files)])) {
        HuginHome <- paste("/Applications", HuginDir[1], sep = "/")

        if(length(HuginDir) >= 2)
          warning("using HUGINHOME:", HuginHome)

        Sys.setenv(HUGINHOME = HuginHome)
      }

      else {
        warning("RHugin did not find Hugin in the expected location")
      }
    }
  }

  else {
    if(nchar(Sys.getenv("HUGINHOME")) == 0) {
      if(file.exists("/usr/local/hugin"))
        Sys.setenv(HUGINHOME = "/usr/local/hugin")

      else {
        warning("RHugin did not find Hugin in the expected location")
      }
    }
  }

  library.dynam("RHugin")
  invisible(NULL)
}


