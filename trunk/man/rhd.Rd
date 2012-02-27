\name{rhd}
\alias{read.rhd}
\alias{write.rhd}

\title{Read/Write RHugin Domains}

\description{
Save an RHugin domain as a Hugin Knowledge Base or NET file or load an RHugin domain from a Hugin Knowledge Base or NET file.
}

\usage{
read.rhd(filename, type = c("auto", "hkb", "net"), password = NULL,
         generate.tables = TRUE)
write.rhd(domain, filename, type = c("hkb", "net"), password = NULL)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{filename}{a character string.}
  \item{type}{a character string specifying the file type.  By default \code{write.rhd} creates  hkb files and \code{read.rhd} guesses the file type from the \code{filename} suffix.}
  \item{password}{either \code{NULL} or a character string specifying the password embedded into the Hugin Knowledge Base file.  NET files do not support passwords.}
  \item{generate.tables}{a logical value.  If \code{TRUE} then, for each node in the domain that has a model, the conditional probability table is generated from the model and the model is discarded.}
}

\value{
  \item{read.rhd}{if successful an RHugin domain, otherwise \code{NULL}.}
  \item{write.rhd}{an integer vector of length one containing the Hugin error code is invisibly returned.  A value of \code{0} indicates that the file was successfully written.}
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_kb_load_domain}, \code{h_net_parse_domain}, \code{h_domain_save_as_kb} and \code{h_domain_save_as_net}.
}

\author{Kjell Konis \email{kjell.konis@me.com}}

\seealso{
  The \code{\link{layoutRHugin}} function to automatically layout a network.
}

\keyword{file}


