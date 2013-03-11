\name{uncompile}
\alias{uncompile}

\title{Uncompile}

\description{
Remove the data structures produced by the compile and triangulate functions.
}

\usage{
uncompile(domain)
}

\arguments{
  \item{domain}{an RHugin domain.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_domain_uncompile}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("apple", echo = FALSE)

# Compile the domain
compile(apple)

# Uncompile the domain
uncompile(apple)
}

\keyword{programming}


