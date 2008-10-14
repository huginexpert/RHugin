\name{compile}
\alias{compile}

\title{Compile an RHugin Domain}

\description{
Compile an RHugin domain using the default triangulation method (unless the domain has already been triangulated).  The domain must contain at least one chance or decision node.
}

\usage{
compile(domain, save = FALSE)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{save}{a logical value.  If \code{TRUE} then copies of the initial belief and junction tree tables of \code{domain} are stored.}
}

\details{
Compiling a domain with \code{save = TRUE} approximately doubles its memory consumption.  However, calls to \code{\link{initialize.domain}} will be significantly faster since the tables can be read from memory rather than recomputed.  A memory backup is automatically kept up-to-date (for example, when a conditional probability table is modified).  The memory backup will be deleted as part of any uncompilation or compression operation.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_domain_compile} and \code{h_domain_save_to_memory}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{initialize.domain}}.
}

\examples{
demo("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)
}

\keyword{programming}


