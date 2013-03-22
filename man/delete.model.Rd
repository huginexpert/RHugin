\name{delete.model}
\alias{delete.model}

\title{Delete Model}

\description{
Delete a node's model.
}

\usage{
delete.model(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_model_delete}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("asia", echo = FALSE)

# Add an empty model to node Either
get.model(asia, "Either")

# Delete the model for Either
delete.model(asia, "Either")
}

\keyword{programming}


