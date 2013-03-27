\name{clone.domain}
\alias{clone.domain}

\title{Clone Domain}

\description{
Create a clone of \code{domain}.
}

\usage{
clone.domain(domain)
}

\arguments{
  \item{domain}{an RHugin domain.}
}

\details{
The clone is a separate domain in the Hugin Decision Engine (HDE) that is identical to \code{domain} except that it is not compiled (even if \code{domain} is).
}

\value{
  an RHugin domain containing the clone.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_domain_clone}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("asia", echo = FALSE)
asia.clone <- clone.domain(asia)
}

\keyword{programming}


