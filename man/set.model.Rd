\name{set.model}
\alias{set.model}

\title{Set Model}

\description{
Set the model for a node.
}

\usage{
set.model(domain, node, model)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{model}{a data.frame containing the R representation of the model for \code{node}.}
}

\details{
Details to come.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_set_model}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("asia", echo = FALSE)
}

\keyword{programming}


