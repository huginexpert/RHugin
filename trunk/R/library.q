.First.lib <- function(libname, pkgname)
{
  if(Sys.info()["sysname"] == "Windows") {

    path <- Sys.getenv("PATH")

    if(length(grep("HDE7.5C", path)) == 0) {

      HuginVersions <- c("Hugin Researcher 7.5",
                         "Hugin Lite 7.5")

      HuginDllPaths <- paste(Sys.getenv("PROGRAMFILES"),
                            "Hugin Expert",
                             HuginVersions,
                            "HDE7.5C\\Lib\\VC10\\Release\\hugin2-7.5-vc10.dll",
                             sep = "\\")

      if(length(HuginVersion <- which(file.exists(HuginDllPaths)))) {

        HuginVersion <- HuginVersions[HuginVersion[1]]

        HuginPath <- paste(Sys.getenv("PROGRAMFILES"),
                          "Hugin Expert",
                           HuginVersion,
                          "HDE7.5C\\Lib\\VC10\\Release",
                           sep = "\\")

        Sys.setenv(PATH = paste(path, HuginPath, sep= ";"))
      }

      else {
        warning("RHugin did not find Hugin in the standard location")
      }
    }
  }

  else if(Sys.info()["sysname"] == "Darwin") {

    if(nchar(Sys.getenv("HUGINHOME")) == 0) {

      HuginHomes <- list.files("/Applications", pattern = "*HDE7.5*",
                                full.names = TRUE)

      if(!length(HuginHomes))
        warning("RHugin did not find Hugin in the standard location")

      else {
        HuginHome <- HuginHomes[1]

        if(length(HuginHomes) > 1)
          warning("multiple Hugin installations found, using: ", HuginHome)

        Sys.setenv(HUGINHOME = HuginHome)
      }
    }
  }

  else {
    if(nchar(Sys.getenv("HUGINHOME")) == 0) {
      if(file.exists("/usr/local/hugin"))
        Sys.setenv(HUGINHOME = "/usr/local/hugin")

      else {
        warning("RHugin did not find Hugin in the standard location")
      }
    }
  }

  library.dynam("RHugin")
  invisible(NULL)
}


