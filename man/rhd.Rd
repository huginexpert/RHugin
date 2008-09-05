\name{rhd}
\alias{read.rhd}
\alias{write.rhd}

\title{Read/Write RHugin Domains}

\description{
  Save an RHugin domain object as a Hugin Knowledge Base or NET file or load an RHugin domain object from a Hugin Knowledge Base or NET file.
}

\usage{
read.rhd(filename, type = c("auto", "hkb", "net"), password = NULL)
write.rhd(domain, filename, type = c("hkb", "net"), password = NULL)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{filename}{a character string.}
  \item{type}{a character string specifying the file type.  By default \code{write.rhd} creates  hkb files and \code{read.rhd} guesses the file type from the \code{filename} suffix.}
  \item{password}{either \code{NULL} or a character string specifying the password embedded into the Hugin Knowledge Base file.  NET files do not support passwords.}
}

\value{
  \item{read.rhd}{if successful an RHugin domain object, otherwise \code{NULL}}
  \item{write.rhd}{an integer vector of length one containing the Hugin error code is invisibly returned.  A value of \code{0} indicates that the file was successfully written.}
}

\seealso{
  The \code{\link{position.nodes}} function to automatically layout a network.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\keyword{file}


