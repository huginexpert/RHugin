\name{hkb}
\alias{read.hkb}
\alias{write.hkb}

\title{Read and Write Hugin Knowledge Base Files}

\description{
  Save an RHugin domain object as a Hugin Knowledge Base file or load an RHugin domain object from an existing Hugin Knowledge Base file.
}

\usage{
read.hkb(filename, password = NULL)
write.hkb(domain, filename, password = NULL)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{filename}{a character vector of length one giving the name of the Hugin Knowledge Base file.}
  \item{password}{either \code{NULL} or a character vector of length one specifying the password embedded into the Hugin Knowledge Base file.}
}

\details{
  RHugin domains created with this package do not contain any graphical information; hence they look quite weird when loaded in the Hugin GUI.
}

\value{
  \item{read.hkb}{if successful an RHugin domain object, otherwise \code{NULL}}
  \item{write.hkb}{an integer vector of length one containing the Hugin error code returned by the Hugin API call is invisibly returned.  A returned value of \code{0} indicates that the Hugin Knowledge Base file was successfully written.}
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\keyword{file}


