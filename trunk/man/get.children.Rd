\name{get.children}
\alias{get.children}

\title{Get Children}

\description{
  Return the names of the child node(s) of \code{node}.
}

\usage{
get.children(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string naming one node in \code{domain}.}
}

\value{
a character vector containing the names of the child nodes of \code{node}.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_get_children}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("limid", echo = FALSE)
plot(limid)

get.children(limid, "Dry")
}

\keyword{programming}


